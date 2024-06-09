using Avalonia.Controls;
using Avalonia.Media;
using Avalonia;
using System.Collections.Generic;
using Avalonia.Input;

namespace Palette.ViewModels
{
    public class PaletteViewModel : ViewModelBase
    {
        public static List<Button> CreateButtons(ref Grid mainGrid, int rows, int columns, bool isSetColors = false, bool isSetThickness = false)
        {
            string[] colors = ["#FF0000", "#FFA500", "#FFFF00", "#008000", "#0000FF", "#4B0082", "#EE82EE", "#800000", "#FFFFF0", "#F0E68C", "#FFE4B5", "#7FFF00", "#643B72", "#FF00FF", "#FFD700", "#32CD32", "#4682B4", "#8A2BE2", "#A0522D", "#87CEEB", "#000080", "#8B4513", "#F5F5DC", "#4169E1", "#9932CC", "#8B0000", "#A0522D", "#8B008B", "#6B8E23", "#483D8B", "#B22222", "#B8860B", "#8B4513", "#2E8B57", "#3CB371", "#808000", "#7CFC00", "#00FF7F", "#FF6347", "#40E0D0", "#FF4500", "#8B008B", "#2E8B57", "#4682B4", "#D2691E", "#DAA520", "#5F9EA0", "#191970"];

            int count = 0;
            List<Button> buttons = [];

            for (int i = 0; i < rows; i++)
            {
                mainGrid.RowDefinitions.Add(new RowDefinition(new GridLength(1, GridUnitType.Star)));
                Grid grid = new Grid();

                for (int j = 0; j < columns; j++)
                {
                    grid.ColumnDefinitions.Add(new ColumnDefinition(new GridLength(1, GridUnitType.Star)));

                    Button button = new Button()
                    {
                        Width = 40,
                        Height = 35,
                        VerticalAlignment = Avalonia.Layout.VerticalAlignment.Center,
                        HorizontalAlignment = Avalonia.Layout.HorizontalAlignment.Center,
                        BorderBrush = SolidColorBrush.Parse("Black")
                    };

                    if (i == 0 && j == 0 && isSetThickness)
                        button.BorderThickness = new Thickness(3);

                    if (isSetColors)
                    {
                        button.Background = SolidColorBrush.Parse(colors[count]);
                        if (count + 1 < colors.Length)
                            count++;
                    }
                    else
                    {
                        button.Background = SolidColorBrush.Parse("White");
                    }

                    buttons.Add(button);
                    grid.Children.Add(button);
                    Grid.SetColumn(button, j);
                }

                grid.ColumnDefinitions.Add(new ColumnDefinition(new GridLength(10)));
                mainGrid.Children.Add(grid);
                Grid.SetRow(grid, i + 1);
            }

            return buttons;
        }

        public static (string, int)? GetIfValid(TextBox textBox, Key key)
        {
            if (!(key >= Key.D0 && key <= Key.D9 || key == Key.Back))
            {
                return null;
            }

            if (textBox.Text == null)
            {
                return null;
            }

            string text = textBox.Text;
            int careIndex = textBox.CaretIndex;

            if (key == Key.Back)
            {
                try
                {
                    int oldIndex = careIndex;
                    if (careIndex - 1 >= 0)
                        careIndex -= 1;

                    if (oldIndex - careIndex > 0)
                        text = text.Remove(careIndex, 1);
                }
                catch
                {
                    return null;
                }
            }
            else
            {
                string textToAdd = key.ToString().Substring(1);
                if (text.Length == careIndex)
                {
                    text += textToAdd;
                    careIndex = text.Length;
                }
                else
                {
                    string newText = "";
                    for (int i = 0; i < careIndex; i++)
                    {
                        newText += text[i];
                    }
                    int length = newText.Length + 1;
                    text = newText + textToAdd + text.Substring(careIndex);
                    careIndex = length;
                }
            }

            if (text.StartsWith('0') && !text.Equals("0"))
                return null;

            return (text, careIndex);
        }
    }
}
