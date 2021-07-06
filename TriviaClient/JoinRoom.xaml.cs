using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.UI;
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
    public sealed partial class JoinRoom : Page
    {
        const int CODE_JOIN_ROOM = 207, CODE_GET_ROOMS = 205;
        List<RoomData> roomsData;
        int chosenRoomId = 0;
        RoomData chosenRoom;
        public JoinRoom()
        {
            this.InitializeComponent();
            this.roomsData = new List<RoomData>();
            showRooms();
        }

        private void refreshButton_Click(object sender, RoutedEventArgs e)
        {
            showRooms();
        }

        private void moveTCreateRoomButton_Click(object sender, RoutedEventArgs e)
        {
            Frame.Navigate(typeof(CreateRoom));
        }

        private void GridView_ItemClick(object sender, ItemClickEventArgs e)
        {
            this.chosenRoom = ((RoomData)e.ClickedItem); ;
            this.chosenRoomId = this.chosenRoom.id;
        }

        private void joinRoom_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                SocketConnection.SendMessage(CODE_JOIN_ROOM, "{\"roomId\": " + this.chosenRoomId + "}");
                if (Deserializer.StatusDeserializer(SocketConnection.ReadMessage()).status == 1)
                {
                    Global.isAdmin = false;
                    Frame.Navigate(typeof(WaitingRoom), this.chosenRoom);
                }
                else
                {
                    SocketConnection.dialogUpdate("Error!", "Problem in joining room " + this.chosenRoomId + ".");
                }
            }
            catch (Exception ex)
            {
                SocketConnection.dialogUpdate("Error!", ex.Message);
            }
        }

        private void showRooms()
        {
            try
            {
                SocketConnection.SendMessage(CODE_GET_ROOMS, "{}");
                this.roomsData = Deserializer.GetRoomDeserializer(SocketConnection.ReadMessage());
            }
            catch (Exception ex)
            {
                SocketConnection.dialogUpdate("Error!", ex.Message);
            }
        }
    }
}

