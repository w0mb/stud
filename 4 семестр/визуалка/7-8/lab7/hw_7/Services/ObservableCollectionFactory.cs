using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Collections.Specialized;
using System.Linq;
using System.Reactive.Linq;
using System.Reactive;
using System.Text;
using System.Threading.Tasks;
using System.ComponentModel;
using CommunityToolkit.Mvvm.ComponentModel;

namespace hw_7.Services
{
    static class ObservableCollectionFactory
    {
        public static IObservable<EventPattern<NotifyCollectionChangedEventArgs>> CreateCollectionObserver<T>(ObservableCollection<T> collection)
        {
            var observable = Observable.Create<EventPattern<NotifyCollectionChangedEventArgs>>(observer =>
           {
               NotifyCollectionChangedEventHandler collectionEventsHandler = (sender, args) =>
                   observer.OnNext(new EventPattern<NotifyCollectionChangedEventArgs>(sender, args));

               collection.CollectionChanged += collectionEventsHandler;

               return () => collection.CollectionChanged -= collectionEventsHandler;
           });

            return observable;
        }

        public static IObservable<EventPattern<PropertyChangedEventArgs>> CreateItemsObserver<T>(ObservableCollection<T> collection)
            where T : ObservableObject
        {
            var observable = Observable.Create<EventPattern<PropertyChangedEventArgs>>(observer =>
            {
                PropertyChangedEventHandler itemEventsHandler = (sender, args) =>
                    observer.OnNext(new EventPattern<PropertyChangedEventArgs>(sender, args));

                foreach (var item in collection)
                {
                    item.PropertyChanged += itemEventsHandler;
                }

                NotifyCollectionChangedEventHandler collectionChangedHandler = (sender, e) =>
                {
                    if (e.NewItems != null)
                    {
                        foreach (T newItem in e.NewItems)
                        {
                            newItem.PropertyChanged += itemEventsHandler;
                        }
                    }

                    if (e.OldItems != null)
                    {
                        foreach (T oldItem in e.OldItems)
                        {
                            oldItem.PropertyChanged -= itemEventsHandler;
                        }
                    }
                };

                collection.CollectionChanged += collectionChangedHandler;

                return () =>
                {
                    foreach (var item in collection)
                    {
                        item.PropertyChanged -= itemEventsHandler;
                    }

                    collection.CollectionChanged -= collectionChangedHandler;
                };
            });

            return observable;
        }
    }
}
