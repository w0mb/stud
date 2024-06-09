using Avalonia.Controls;
using Avalonia.Controls.Primitives;
using System;
using Avalonia.Media;
using Avalonia.Input;
using System.Linq;
using System.Collections.Generic;
using Avalonia;
using Rectangle = Avalonia.Controls.Shapes.Rectangle;
using Palette.ViewModels;
using Color = Avalonia.Media.Color;
using Avalonia.Interactivity;
using Key = Avalonia.Input.Key;

namespace Palette.Controls
{
    public class Palette : TemplatedControl
    {
        private ColorSpectrum _colorSpectrum;
        private ColorSlider _colorSlider;
        private Rectangle _colorPreviewer;
        private List<Button> _buttons;
        private Dictionary<string, TextBox> _textBoxesDict;

        public Palette()
        {
            _colorPreviewer = new Rectangle();
            _colorSpectrum = new ColorSpectrum();
            _colorSlider = new ColorSlider();
            _buttons = [];
            _textBoxesDict = [];
        }

        protected override void OnApplyTemplate(TemplateAppliedEventArgs e)
        {
            base.OnApplyTemplate(e);

            var basicsColorsGrid = e.NameScope.Find<Grid>("BasicsColorsGrid");
            var customColorsFirstGrid = e.NameScope.Find<Grid>("CustomColorsFirstGrid");
            var customColorsSecondGrid = e.NameScope.Find<Grid>("CustomColorsSecondGrid");

            if (basicsColorsGrid == null || customColorsFirstGrid == null || customColorsSecondGrid == null)
                return;

            var newButtons = PaletteViewModel.CreateButtons(ref basicsColorsGrid, 6, 8, true);
            foreach (var button in newButtons)
            {
                button.Tapped += ColorButton_Tapped;
            }
            newButtons = PaletteViewModel.CreateButtons(ref customColorsFirstGrid, 2, 8, false, true);
            newButtons = newButtons.Concat(PaletteViewModel.CreateButtons(ref customColorsSecondGrid, 2, 8)).ToList();
            foreach (var button in newButtons)
            {
                button.Tapped += ColorButton_Tapped;
                _buttons.Add(button);
            }

            _colorSpectrum = e.NameScope.Find<ColorSpectrum>("ColorSpectrum");
            _colorSlider = e.NameScope.Find<ColorSlider>("ColorSlider");
            _colorPreviewer = e.NameScope.Find<Rectangle>("ColorPreviewer");

            if (_colorSpectrum != null && _colorSlider != null)
            {
                _colorSpectrum.ColorChanged += ColorElement_ColorChanged;
                _colorSlider.ColorChanged += ColorElement_ColorChanged;
            }

            _textBoxesDict["HueTextBox"] = e.NameScope.Find<TextBox>("HueTextBox");
            _textBoxesDict["HueTextBox"].AddHandler(KeyDownEvent, new EventHandler<KeyEventArgs>(HslTextBox_KeyDown), RoutingStrategies.Tunnel);

            _textBoxesDict["SatTextBox"] = e.NameScope.Find<TextBox>("SatTextBox");
            _textBoxesDict["SatTextBox"].AddHandler(KeyDownEvent, new EventHandler<KeyEventArgs>(HslTextBox_KeyDown), RoutingStrategies.Tunnel);

            _textBoxesDict["LumTextBox"] = e.NameScope.Find<TextBox>("LumTextBox");
            _textBoxesDict["LumTextBox"].AddHandler(KeyDownEvent, new EventHandler<KeyEventArgs>(HslTextBox_KeyDown), RoutingStrategies.Tunnel);

            _textBoxesDict["RedTextBox"] = e.NameScope.Find<TextBox>("RedTextBox");
            _textBoxesDict["RedTextBox"].AddHandler(KeyDownEvent, new EventHandler<KeyEventArgs>(RgbTextBox_KeyDown), RoutingStrategies.Tunnel);

            _textBoxesDict["GreenTextBox"] = e.NameScope.Find<TextBox>("GreenTextBox");
            _textBoxesDict["GreenTextBox"].AddHandler(KeyDownEvent, new EventHandler<KeyEventArgs>(RgbTextBox_KeyDown), RoutingStrategies.Tunnel);

            _textBoxesDict["BlueTextBox"] = e.NameScope.Find<TextBox>("BlueTextBox");
            _textBoxesDict["BlueTextBox"].AddHandler(KeyDownEvent, new EventHandler<KeyEventArgs>(RgbTextBox_KeyDown), RoutingStrategies.Tunnel);

            var addColorButton = e.NameScope.Find<Button>("AddColorButton");
            if (addColorButton != null)
            {
                addColorButton.Tapped += AddColorButton_Tapped;
            }
        }

        private void HslTextBox_KeyDown(object? sender, KeyEventArgs e)
        {
            if (sender is TextBox textBox)
            {
                if (e.Key == Key.Left || e.Key == Key.Right) { return; }

                e.Handled = true;

                var result = PaletteViewModel.GetIfValid(textBox, e.Key);

                if (result == null) { return; }

                string text = result.Value.Item1;
                int careIndex = result.Value.Item2;

                if (string.IsNullOrEmpty(text))
                {
                    textBox.Text = text;
                    textBox.CaretIndex = careIndex;
                    return;
                }

                HslColor hslColor = _colorSpectrum.Color.ToHsl();
                Color newColor = new Color();

                double value;
                switch (textBox.Name)
                {
                    case "HueTextBox":
                        if (!double.TryParse(text, out value) || value > 359)
                        {
                            return;
                        }
                        newColor = new HslColor(hslColor.A, (int)value, hslColor.S, hslColor.L).ToRgb();
                        break;
                    case "SatTextBox":
                        if (!double.TryParse(text, out value) || value > 100)
                        {
                            return;
                        }
                        newColor = new HslColor(hslColor.A, hslColor.H, value / 100, hslColor.L).ToRgb();
                        break;
                    case "LumTextBox":
                        if (!double.TryParse(text, out value) || value > 100)
                        {
                            return;
                        }
                        newColor = new HslColor(hslColor.A, hslColor.H, hslColor.S, value / 100).ToRgb();
                        break;
                }

                textBox.Text = text;
                textBox.CaretIndex = careIndex;

                UpdateColors(newColor);
            }
        }

        private void RgbTextBox_KeyDown(object? sender, KeyEventArgs e)
        {
            if (sender is TextBox textBox)
            {
                if (e.Key == Key.Left || e.Key == Key.Right) { return; }

                e.Handled = true;

                var result = PaletteViewModel.GetIfValid(textBox, e.Key);

                if (result == null) { return; }

                string text = result.Value.Item1;
                int careIndex = result.Value.Item2;

                if (string.IsNullOrEmpty(text))
                {
                    textBox.Text = text;
                    textBox.CaretIndex = careIndex;
                    return;
                }

                if (!int.TryParse(text, out int value) || value > 255)
                {
                    return;
                }

                textBox.Text = text;
                textBox.CaretIndex = careIndex;

                Color color = _colorSpectrum.Color;
                Color newColor = new Color();

                switch (textBox.Name)
                {
                    case "RedTextBox":
                        newColor = new Color(color.A, (byte)value, color.G, color.B);
                        break;
                    case "GreenTextBox":
                        newColor = new Color(color.A, color.R, (byte)value, color.B);
                        break;
                    case "BlueTextBox":
                        newColor = new Color(color.A, color.R, color.G, (byte)value);
                        break;
                }

                UpdateColors(newColor);
            }
        }

        private void UpdateColors(Color color)
        {
            _colorSpectrum.ColorChanged -= ColorElement_ColorChanged;
            _colorSlider.ColorChanged -= ColorElement_ColorChanged;

            _colorSpectrum.Color = color;
            _colorSlider.Color = color;
            _colorPreviewer.Fill = new SolidColorBrush(color);

            _colorSpectrum.ColorChanged += ColorElement_ColorChanged;
            _colorSlider.ColorChanged += ColorElement_ColorChanged;
        }

        private void UpdateTextBoxes(Color color)
        {
            foreach (var pair in _textBoxesDict)
            {
                switch (pair.Key)
                {
                    case "HueTextBox":
                        pair.Value.Text = ((int)color.ToHsl().H).ToString();
                        break;
                    case "SatTextBox":
                        pair.Value.Text = ((int)(color.ToHsv().S * 100)).ToString();
                        break;
                    case "LumTextBox":
                        pair.Value.Text = ((int)(color.ToHsl().L * 100)).ToString();
                        break;
                    case "RedTextBox":
                        pair.Value.Text = color.R.ToString();
                        break;
                    case "GreenTextBox":
                        pair.Value.Text = color.G.ToString();
                        break;
                    case "BlueTextBox":
                        pair.Value.Text = color.B.ToString();
                        break;
                }

                if (pair.Value.Text != null)
                    pair.Value.CaretIndex = pair.Value.Text.Length;
            }
        }

        private void ColorButton_Tapped(object? sender, TappedEventArgs e)
        {
            if (sender is Button tappedButton)
            {
                bool isFound = false;
                Button? selectedButton = null;
                foreach (Button button in _buttons)
                {
                    if (button == tappedButton)
                    {
                        isFound = true;
                    }

                    if (button.BorderThickness != new Thickness(1))
                    {
                        selectedButton = button;
                    }
                }

                if (isFound && selectedButton != null)
                {
                    selectedButton.BorderThickness = new Thickness(1);
                    tappedButton.BorderThickness = new Thickness(3);
                }

                var solidColorBrush = (SolidColorBrush?)tappedButton.Background;
                if (solidColorBrush != null)
                {
                    UpdateColors(solidColorBrush.Color);
                    UpdateTextBoxes(solidColorBrush.Color);
                }
            }
        }

        private void AddColorButton_Tapped(object? sender, TappedEventArgs e)
        {
            if (sender is not Button)
                return;

            for (int i = 0; i < _buttons.Count; i++)
            {
                Thickness thickness = new Thickness(1);
                if (_buttons[i].BorderThickness != thickness)
                {
                    _buttons[i].Background = _colorPreviewer.Fill;

                    int index;
                    if (i + 1 >= _buttons.Count)
                        index = 0;
                    else
                        index = i + 1;

                    _buttons[index].BorderThickness = _buttons[i].BorderThickness;
                    _buttons[i].BorderThickness = thickness;
                    return;
                }
            }
        }

        private void ColorElement_ColorChanged(object? sender, ColorChangedEventArgs e)
        {
            Color color = e.NewColor;

            UpdateTextBoxes(color);

            if (sender is ColorSpectrum)
            {
                _colorSlider.Color = color;
            }

            else if (sender is ColorSlider)
            {
                _colorSpectrum.Color = color;
            }

            _colorPreviewer.Fill = new SolidColorBrush(color);
        }
    }
}
