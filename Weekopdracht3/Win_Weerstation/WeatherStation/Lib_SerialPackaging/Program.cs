using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using Lib_SerialPackaging.Lib;

namespace Lib_SerialPackaging
{
    class Program
    {

        private ArduinoSerialCom serial;
        private static Thread _workerThread;

        static void Main(string[] args)
        {
            Program p = new Program();
            _workerThread = new Thread(()=>p.Connect());
            _workerThread.Start();
            Console.WriteLine("Press any key to close");
            Console.ReadLine();
            p.Close();
        }

        public void Connect()
        {
            string[] ports = ArduinoSerialCom.GetPortNames();
            Console.WriteLine("Amount of ports: " + ports.Length);
            if (ports.Length > 0)
            {
                Console.WriteLine("Connecting to: " + ports[0]);
                serial = new ArduinoSerialCom(ports[0]);
                
                serial.OnNewValueEvent +=OnNewValueEvent;
                serial.Open();
                Console.WriteLine("Waiting for messages");
            }
        }

        public void Close()
        {
            serial.Close();
        }

        private void OnNewValueEvent(object sender, ArduinoSerialCom.ValueChangedEventArgs valueChangedEventArgs)
        {
            Console.WriteLine("New value in index:" + valueChangedEventArgs.Index);
            Console.WriteLine("Value:" + serial.getValue(valueChangedEventArgs.Index).ToString());
        }
    }
}
