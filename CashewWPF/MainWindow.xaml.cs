using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using CashewLogicDLL;

namespace CashewWPF
{

    public partial class MainWindow : Window
    {
        CashewLogic CashewObj = new CashewLogic();
        String[] Methods = { "Regula Falsi", "Secant", "Mullers", "Crouts-Cholesky", "Gauss-Jordan", "Gauss-Seidel" };
        String[] Methods2 = { "Linear Regression", "Newtons Interpolation", "Trapezoidal Rule", "Simpsons 1/3 Rule", "Simpsons 3/8 Rule", "Forward FDD", "Backward FDD", "Centered FDD"};


        public MainWindow()
        {
            InitializeComponent();
            Cmbo_Method.ItemsSource = Methods;
            Cmbo_Method2.ItemsSource = Methods2;
            CashewObj.ItrProp = 1000;
            CashewObj.AbsProp = 0.0001;
            CashewObj.RelProp = 0;
        }

        private void Click_Setting(object sender, RoutedEventArgs e)
        {
            if (Grid_Content.Visibility == Visibility.Visible)
            {
                Grid_Settings.Visibility = Visibility.Visible;
                Grid_Content.Visibility = Visibility.Collapsed;
            }
            else
            {
                Grid_Content.Visibility = Visibility.Visible;
                Grid_Settings.Visibility = Visibility.Collapsed;
            }
        }

        private void SaveSettings(object sender, RoutedEventArgs e)
        {
            CashewObj.ItrProp = int.Parse(Tbox_SetItr.Text);
            if (Rad_Abs.IsChecked == true)
            {
                CashewObj.AbsProp = double.Parse(Tbox_SetAbs.Text);
                CashewObj.RelProp = 0;
            }
            else
            {
                CashewObj.AbsProp = 0;
                CashewObj.RelProp = double.Parse(Tbox_SetRel.Text);
            }

        }

        private void Cmbo_Method_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            int sel = Cmbo_Method.SelectedIndex;
            Tblk_Disp.Text = "";

            if (sel == 0 || sel == 1)
            {
                //For Regula and Secant
                Tblk_Init0.Visibility = Visibility.Visible;
                Tbox_Init0.Visibility = Visibility.Visible;
                Tblk_Init1.Visibility = Visibility.Visible;
                Tbox_Init1.Visibility = Visibility.Visible;

                Tblk_Init2.Visibility = Visibility.Collapsed;
                Tbox_Init2.Visibility = Visibility.Collapsed;
            }
            else if (sel == 2)
            {
                //For Mullers
                Tblk_Init0.Visibility = Visibility.Visible;
                Tbox_Init0.Visibility = Visibility.Visible;
                Tblk_Init1.Visibility = Visibility.Visible;
                Tbox_Init1.Visibility = Visibility.Visible;
                Tblk_Init2.Visibility = Visibility.Visible;
                Tbox_Init2.Visibility = Visibility.Visible;
            }
            else
            {
                //Direct Methods
                Tblk_Init0.Visibility = Visibility.Collapsed;
                Tbox_Init0.Visibility = Visibility.Collapsed;
                Tblk_Init1.Visibility = Visibility.Collapsed;
                Tbox_Init1.Visibility = Visibility.Collapsed;
                Tblk_Init2.Visibility = Visibility.Collapsed;
                Tbox_Init2.Visibility = Visibility.Collapsed;
            }
        }

        private void But_Calc_Click(object sender, RoutedEventArgs e)
        {
            int sel = Cmbo_Method.SelectedIndex;
            switch (sel)
            {
                case 0:
                    {
                        Tblk_Disp.Text = CashewObj.ImpRegula(Tbox_Express.Text, double.Parse(Tbox_Init0.Text), double.Parse(Tbox_Init1.Text)).ToString();
                        break;
                    }
                case 1:
                    {
                        Tblk_Disp.Text = CashewObj.ImpSecant(Tbox_Express.Text, double.Parse(Tbox_Init0.Text), double.Parse(Tbox_Init1.Text)).ToString();
                        break;
                    }
                case 2:
                    {
                        Tblk_Disp.Text = CashewObj.ImpMuller(Tbox_Express.Text, double.Parse(Tbox_Init0.Text), double.Parse(Tbox_Init1.Text), double.Parse(Tbox_Init2.Text)).ToString();
                        break;
                    }
                case 3:
                    {
                        Tblk_Disp.Text = CashewObj.ImpCClsky(Tbox_Express.Text);
                        break;
                    }
                case 4:
                    {
                        Tblk_Disp.Text = CashewObj.ImpGJcobi(Tbox_Express.Text);
                        break;
                    }
                case 5:
                    {
                        Tblk_Disp.Text = CashewObj.ImpGSeidl(Tbox_Express.Text);
                        break;
                    }

            }
        }

        private void Cmbo_Method2_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            int sel = Cmbo_Method2.SelectedIndex;
            Tblk2_Disp.Text = "";
            if (sel == 0 || sel == 1)
            {
                Grid_DataPoints.Visibility = Visibility.Visible;

                Tblk2_Init0.Visibility = Visibility.Collapsed;
                Tblk2_Init1.Visibility = Visibility.Collapsed;
                Tbox2_Express.Visibility = Visibility.Collapsed;

                Tbox2_Init0.Visibility = Visibility.Collapsed;
                Tbox2_Init1.Visibility = Visibility.Collapsed;
            }
            if (sel == 2 || sel == 3 || sel == 4)
            {
                Grid_DataPoints.Visibility = Visibility.Collapsed;

                Tblk2_Init0.Visibility = Visibility.Visible;
                Tblk2_Init1.Visibility = Visibility.Visible;
                Tbox2_Express.Visibility = Visibility.Visible;

                Tbox2_Init0.Visibility = Visibility.Visible;
                Tbox2_Init1.Visibility = Visibility.Visible;

            }
            if (sel == 5 || sel == 6 || sel == 7)
            {
                Grid_DataPoints.Visibility = Visibility.Collapsed;

                Tblk2_Init0.Visibility = Visibility.Visible;
                Tblk2_Init1.Visibility = Visibility.Collapsed;
                Tbox2_Express.Visibility = Visibility.Visible;

                Tbox2_Init0.Visibility = Visibility.Visible;
                Tbox2_Init1.Visibility = Visibility.Collapsed;
            }
        }

        private void But2_Calc_Click(object sender, RoutedEventArgs e)
        {
            int sel = Cmbo_Method2.SelectedIndex;

            switch(sel)
            {
                case 0:
                    Tblk2_Disp.Text = CashewObj.ImpLReggression(Tbox2_X.Text, Tbox2_FX.Text).ToString();
                    break;
                case 1:
                    
                    Tblk2_Disp.Text = CashewObj.ImpNewtonsDDiff(Tbox2_X.Text, Tbox2_FX.Text).ToString();
                    break;
                case 2:
                    Tblk2_Disp.Text = CashewObj.ImpIntegTrapezd(Tbox2_Express.Text, double.Parse(Tbox2_Init0.Text), double.Parse(Tbox2_Init1.Text), int.Parse(Tbox_SetSeg.Text)).ToString();
                    break;
                case 3:
                    Tblk2_Disp.Text = CashewObj.ImpIntegOneThrd(Tbox2_Express.Text, double.Parse(Tbox2_Init0.Text), double.Parse(Tbox2_Init1.Text), int.Parse(Tbox_SetSeg.Text)).ToString();
                    break;
                case 4:
                    Tblk2_Disp.Text = CashewObj.ImpIntegThreEht(Tbox2_Express.Text, double.Parse(Tbox2_Init0.Text), double.Parse(Tbox2_Init1.Text), int.Parse(Tbox_SetSeg.Text)).ToString();
                    break;
                case 5:
                    Tblk2_Disp.Text = CashewObj.ImpForwardDDiff(Tbox2_Express.Text, double.Parse(Tbox2_Init0.Text), double.Parse(Tbox_SetStep.Text)).ToString();
                    break;
                case 6:
                    Tblk2_Disp.Text = CashewObj.ImpBackwrdDDiff(Tbox2_Express.Text, double.Parse(Tbox2_Init0.Text), double.Parse(Tbox_SetStep.Text)).ToString();
                    break;
                case 7:
                    Tblk2_Disp.Text = CashewObj.ImpCentereDDiff(Tbox2_Express.Text, double.Parse(Tbox2_Init0.Text), double.Parse(Tbox_SetStep.Text)).ToString();
                    break;
            }
        }


    }
}
