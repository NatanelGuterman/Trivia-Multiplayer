using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TriviaClient
{
    struct Status
    {
        public int status;
    }

    struct RoomData
    {
        public int id, maxPlayers, numOfQuestionsInGame, timePerQuestion, isActive;
        public string name;
    }

    static class Deserializer
    {
        const int CODE_AND_LENGTH_BYTES = 5;

        private static string ConvertBytesToAscii(byte[] message)
        {
            string temp = Encoding.ASCII.GetString(message), res = "";
            int i = 0;
            List<byte> list = new List<byte>();

            for (i = 0; i < temp.Length; i += 8)
            {
                list.Add(Convert.ToByte(temp.Substring(i, 8), 2));
            }
            list.RemoveRange(0, CODE_AND_LENGTH_BYTES);
            res = Encoding.ASCII.GetString(list.ToArray());
            return res;
        }
        public static Status StatusDeserializer(byte[] message)
        {
            string res = ConvertBytesToAscii(message);
            Status result = JsonConvert.DeserializeObject<Status>(res);
            return result;
        }

        public static List<RoomData> GetRoomDeserializer(byte[] message)
        {
            string res = ConvertBytesToAscii(message);
            int i = 0;

            res = res.Substring(res.IndexOf(":") + 1, res.Length - res.IndexOf(":") - 2); // Remove "{"Rooms": ......... }"
            string[] temp = res.Split("},"); // Split to each room's data

            string[] allJsons = new string[temp.Length]; // Will contain fixed splited room's data

            // Fix data:
            allJsons[0] = temp[0].Substring(temp[0].IndexOf(":") + 1) + "}";
            allJsons[temp.Length - 1] = temp[temp.Length - 1].Substring(temp[temp.Length - 1].IndexOf(":") + 1, temp[temp.Length - 1].Length - 2 - temp[temp.Length - 1].IndexOf(":"));
            for (i = 1; i < allJsons.Length - 1; i++)
            {
                allJsons[i] = temp[i].Substring(temp[i].IndexOf(":") + 1) + "}";
            }

            // Use JSON to deserialize the strings of json data
            List<RoomData> roomsData = new List<RoomData>();
            for (i = 0; i < allJsons.Length; i++)
            {
                roomsData.Add(JsonConvert.DeserializeObject<RoomData>(allJsons[i]));
            }
            return roomsData;
        }
    }
}
