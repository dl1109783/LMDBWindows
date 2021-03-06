﻿using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace LMDBServiceNet
{
    public class Logger
    {
        private static ReaderWriterLock _rwLock = new ReaderWriterLock();

        public static void LogInfo(string message)
        {
            _rwLock.AcquireWriterLock(10000);

            if (Directory.Exists("c:\\temp\\logs") == false)
            {
                if (Directory.Exists("c:\\temp") == false)
                {
                    Directory.CreateDirectory("c:\\temp");
                }
                Directory.CreateDirectory("c:\\temp\\logs");
            }

            DateTime dt = DateTime.Now;
            string str = String.Format("INFO - {0}.{1} - {2}", dt.ToLongTimeString(), dt.Millisecond, message);

            Console.WriteLine(str);

            TextWriter tw = new StreamWriter("c:\\temp\\logs\\LMDBNet.txt", true);
            tw.WriteLine(str);
            tw.Close();

            _rwLock.ReleaseWriterLock();
        }
    }
}
