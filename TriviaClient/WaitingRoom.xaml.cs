using System;
using System.Collections.Generic;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.UI;
using Windows.UI.Text;
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
            showElementsByUserLevel();
        }

        private void showElementsByUserLevel()
        {
            if (Global.isAdmin)
            {
                startGameButton.Visibility = Visibility.Visible;
                closeRoomButton.Visibility = Visibility.Visible;
                TextBlock userAdmin = new TextBlock() { Text = ">> "  + Global.username};

                userAdmin.FontFamily = new FontFamily("Jetbrains Mono");
                userAdmin.FontWeight = FontWeights.Bold;
                userAdmin.Foreground = new SolidColorBrush(Colors.Black);
                userAdmin.FontSize = 25;
                usersTable.Children.Add(userAdmin);

            }
            else
            {
                leaveRoomButton.Visibility = Visibility.Visible;
            }

        }

        protected override void OnNavigatedTo(NavigationEventArgs e)
        {
            base.OnNavigatedTo(e);
            RoomData roomData = (RoomData)e.Parameter;
            MaximumPlayersResult.Text = roomData.maxPlayers.ToString();
            AmountofQuestionsResult.Text = roomData.numOfQuestionsInGame.ToString();
            TimePerQuestionResult.Text = roomData.timePerQuestion.ToString();
            roomNameTextBlock.Text = ">> Room: " + roomData.name; 
        }
    }
}