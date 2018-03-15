using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using Lib_SerialPackaging.Lib;
using Lib_SerialPackaging.Lib.Models;

namespace WeatherStation
{
    public class Program
    {
        private static Thread _workerThread;
        private ArduinoSerialCom _serial;

        private const int _windDirectionIndex = 0;
        private const int _tempIndex = 1;
        private const int _lightIndex = 2;

        private int _lastWindDirection = 0;
        private double _lastTemp = 0;
        private int _lastLight = 0;

        static void Main(string[] args)
        {
            Program p = new Program();
            _workerThread = new Thread(() => p.Connect());
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
                _serial = new ArduinoSerialCom(ports[0]);

                _serial.OnNewValueEvent += OnNewValueEvent;
                _serial.Open();
                Console.WriteLine("Waiting for messages");
            }
            else
            {
                PrintWeatherMessage();
                Console.WriteLine("No port to connect to");
            }
        }

        public void Close()
        {
            _serial.Close();
        }

        private void OnNewValueEvent(object sender, ArduinoSerialCom.ValueChangedEventArgs valueChangedEventArgs)
        {
            TypeStaticValue value = _serial.getValue(valueChangedEventArgs.Index);
            if (valueChangedEventArgs.Index == _tempIndex && value.getType() == TypeStaticValue.StaticType.INT)
            {
                _lastTemp = (double)value.getIntValue() / 100;
            }
            else if (valueChangedEventArgs.Index == _lightIndex && value.getType() == TypeStaticValue.StaticType.INT)
            {
                _lastLight = value.getIntValue();
            }
            else if (valueChangedEventArgs.Index == _windDirectionIndex && value.getType() == TypeStaticValue.StaticType.INT)
            {
                _lastWindDirection= value.getIntValue();
            }
            PrintWeatherMessage();
        }

        private void PrintWeatherMessage()
        {
            Console.Clear();
            Console.WriteLine(
                $@"
====================Weather======================
|   Temperture:     {_lastTemp}°C
|   Light:          {_lastLight}lux
|   Wind direction: {_lastWindDirection}°
=================================================
"
            );
        }
    }
}
