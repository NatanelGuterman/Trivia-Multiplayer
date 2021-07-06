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
    public sealed partial class CreateRoom : Page
    {
        const int CODE_CREATE_ROOM = 208;
        public CreateRoom()
        {
            this.InitializeComponent();
        }

        private void moveTJoinRoomButton_Click(object sender, RoutedEventArgs e)
        {
            Frame.Navigate(typeof(JoinRoom));
        }

        private void createRoom_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                SocketConnection.SendMessage(CODE_CREATE_ROOM, "{\"roomName\": \"" + roomNameTextBlock.Text + "\", \"maxUsers\": " + int.Parse(maxPlayersTextBlock.Text) + ", \"questionCount\": " + int.Parse(numOfQuestionsTextBlock.Text) + ", \"answerTimeout\": " + int.Parse(timePerQuestionTextBlock.Text) + "}");
                if (Deserializer.StatusDeserializer(SocketConnection.ReadMessage()).status == 1)
                {
                    RoomData createdRoomData;
                    createdRoomData.name = roomNameTextBlock.Text;
                    createdRoomData.maxPlayers = int.Parse(maxPlayersTextBlock.Text);
                    createdRoomData.numOfQuestionsInGame = int.Parse(numOfQuestionsTextBlock.Text);
                    createdRoomData.timePerQuestion = int.Parse(timePerQuestionTextBlock.Text);
                    createdRoomData.id = 0;
                    createdRoomData.isActive = 1;
                    Global.isAdmin = true;
                    Frame.Navigate(typeof(WaitingRoom), createdRoomData);
                }
            }
            catch(Exception ex)
            {
                SocketConnection.dialogUpdate("Error!", ex.Message);
            }
        }
    }
}
