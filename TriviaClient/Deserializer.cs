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

    static class Deserializer
    {
        const int CODE_AND_LENGTH_BYTES = 5;
        public static Status StatusDeserializer(byte[] message)
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
            Status result = JsonConvert.DeserializeObject<Status>(res);
            return result;
        }
    }
}
