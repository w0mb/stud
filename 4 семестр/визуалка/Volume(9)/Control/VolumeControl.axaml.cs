using Avalonia;
using Avalonia.Controls;
using Avalonia.Controls.Primitives;
using Avalonia.Input;
using Avalonia.Media.Imaging;
using System;

namespace Volume.Control
{
    public class VolumeControl : TemplatedControl
    {
        protected override void OnApplyTemplate(TemplateAppliedEventArgs e)
        {
            base.OnApplyTemplate(e);

            var button = e.NameScope.Find<Button>("button");
            if (button != null)
            {
                button.Tapped += ButtonTapped;
            }

            var slider = e.NameScope.Find<Slider>("slider");
            CurrentValue = $"Slider value: {Math.Round(slider.Value, 4)}";

            slider.ValueChanged += (sender, e) =>
            {
                CurrentValue = $"Slider value: {Math.Round(slider.Value, 4)}";
            };
        }

        private void ButtonTapped(object sender, TappedEventArgs e)
        {
            IsExpanded = !IsExpanded;
        }

        public static readonly StyledProperty<Bitmap> IconProperty =
            AvaloniaProperty.Register<VolumeControl, Bitmap>("Icon");

        public Bitmap Icon
        {
            get => GetValue(IconProperty);
            set => SetValue(IconProperty, value);
        }

        public static readonly StyledProperty<bool> IsExpandedProperty = AvaloniaProperty.Register<VolumeControl, bool>("IsExpanded");

        public bool IsExpanded
        {
            get => GetValue(IsExpandedProperty);
            set => SetValue(IsExpandedProperty, value);
        }

        public static readonly StyledProperty<double> MinimumProperty = AvaloniaProperty.Register<VolumeControl, double>("Minimum");

        public double Minimum
        {
            get => GetValue(MinimumProperty);
            set => SetValue(MinimumProperty, value);
        }

        public static readonly StyledProperty<double> MaximumProperty = AvaloniaProperty.Register<VolumeControl, double>("Maximum");

        public double Maximum
        {
            get => GetValue(MaximumProperty);
            set => SetValue(MaximumProperty, value);
        }

        public static readonly StyledProperty<string> CurrentValueProperty = AvaloniaProperty.Register<VolumeControl, string>("CurrentValue");

        public string CurrentValue
        {
            get => GetValue(CurrentValueProperty);
            set => SetValue(CurrentValueProperty, value);
        }
    }
}
