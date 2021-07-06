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
        const int GET_USERS_IN_ROOM_CODE = 206;
        string[] playersInRoom;
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
                TextBlock userAdmin = new TextBlock() { Text = ">> " + Global.username };

                userAdmin.FontFamily = new FontFamily("Jetbrains Mono");
                userAdmin.FontWeight = FontWeights.Bold;
                userAdmin.Foreground = new SolidColorBrush(Colors.Black);
                userAdmin.FontSize = 25;
                usersTable.Children.Add(userAdmin);

            }
            else
            {
                leaveRoomButton.Visibility = Visibility.Visible;
                try
                {
                    SocketConnection.SendMessage(GET_USERS_IN_ROOM_CODE, "{}");
                    this.playersInRoom = Deserializer.GetPlayersInRoom(SocketConnection.ReadMessage())._players;
                    for (int i = 0; i < this.playersInRoom.Length; i++)
                    {
                        TextBlock user = new TextBlock() { Text = ">> " + this.playersInRoom[i] };
                        user.FontFamily = new FontFamily("Jetbrains Mono");
                        user.FontWeight = FontWeights.Bold;
                        user.Foreground = new SolidColorBrush(Colors.Black);
                        user.FontSize = 25;
                        usersTable.Children.Add(user);
                    }

                }
                catch (Exception ex)
                {
                    SocketConnection.dialogUpdate("Error!", ex.Message);
                }
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