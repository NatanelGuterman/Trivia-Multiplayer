using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Navigation;

// The Blank Page item template is documented at https://go.microsoft.com/fwlink/?LinkId=234238

namespace TriviaClient
{
    public sealed partial class WaitingRoom : Page
    {
        public WaitingRoom()
        {
            this.InitializeComponent();
            visibleButtons();
        }


        private void visibleButtons()
        {
            //if (admin)
            //{
            //    startGameButton.Visibility = Visibility.Visible;
            //    closeRoomButton.Visibility = Visibility.Visible;
            //}
            //else
            //{
            //    leaveRoomButton.Visibility = Visibility.Visible;
            //}

        }
    }
}