using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TriviaClient
{
    static class Serializer
    {
        const int CODE_SIZE = 8, MESSAGE_LENGTH = 32, BYTE = 8;
        public static byte[] MessageInBytes(string username, string password, int messageCode, string message)
        {
            string binaryMessage = "";
            int i = 0;
            byte[] buffer;

            binaryMessage = StringToBinaryString(Encoding.UTF8, message);
            buffer = new byte[5 * BYTE + binaryMessage.Length];

            for (i = 0; i < binaryMessage.Length; i++)
            {
                buffer[i + 5 * BYTE] = (byte)int.Parse(binaryMessage[i].ToString());
            }

            binaryMessage = IntToBinaryString(binaryMessage.Length, MESSAGE_LENGTH);
            for (i = 0; i < BYTE * 4; i++)
            {
                buffer[i + BYTE] = (byte)int.Parse(binaryMessage[i].ToString());
            }

            binaryMessage = IntToBinaryString(messageCode, CODE_SIZE);
            for (i = 0; i < BYTE; i++)
            {
                buffer[i] = (byte)int.Parse(binaryMessage[i].ToString());
            }

            for (i = 0; i < buffer.Length; i++)
            {
                Debug.Write(buffer[i]);
                if ((i + 1) % 8 == 0)
                    Debug.Write(" ");
            }

            return buffer;
        }

        private static string StringToBinaryString(Encoding encoding, string text)
        {
            return string.Join("", encoding.GetBytes(text).Select(n => Convert.ToString(n, 2).PadLeft(8, '0')));
        }

        private static string IntToBinaryString(int x, int size)
        {
            if (size == 0)
                size = 32;

            char[] bits = new char[size];
            int i = 0;
            char temp = ' ';

            for (i = 0; i < size; i++)
                bits[i] = '0';
            i = 0;

            while (x != 0)
            {
                bits[i++] = (x & 1) == 1 ? '1' : '0';
                x >>= 1;
            }

            if (size == 32)
            {
                for (i = 0; i < size / 2; i++)
                {
                    temp = bits[i];
                    bits[i] = bits[size - i - 1];
                    bits[size - i - 1] = temp;
                }
            }
            else
            {
                Array.Reverse(bits, 0, i);
            }
            return new string(bits);
        }
    }
}
