using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TriviaClient
{
    struct Status
    {
        int status;
    }

    static class Deserializer
    {

        public static Status Status1Deserializer(byte[] message)
        {
            string temp = Encoding.ASCII.GetString(message), res = "";
            int i = 0;
            List<byte> list = new List<byte>();

            for (i = 0; i < temp.Length; i += 8)
            {
                list.Add(Convert.ToByte(temp.Substring(i, 8), 2));
            }
            res = Encoding.ASCII.GetString(list.ToArray());
            Status result = JsonConvert.DeserializeObject<Status>(res);
            return result;
        }
    }
}
