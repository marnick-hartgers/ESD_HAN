using System;
using System.Collections.Generic;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Lib_SerialPackaging.Lib.Models;

namespace Lib_SerialPackaging.Lib
{
    public class ArduinoSerialCom : ValueDictionary
    {
        private PackageDeserializer _deserializer;
        private SerialPort _port;

        public EventHandler<ValueChangedEventArgs> OnNewValueEvent;

        public static string[] GetPortNames()
        {
            return SerialPort.GetPortNames();
        }

        public ArduinoSerialCom(string port)
        {
            _deserializer = new PackageDeserializer();
            _deserializer.onNewValue += OnNewValue;
            _port = new SerialPort(port);
            _port.BaudRate = 9600;
            _port.DataReceived += _port_DataReceived;
        }

        private void OnNewValue(object sender, PackageDeserializer.ReceivedValueEventArgs receivedValueEventArgs)
        {
            this.setValue(receivedValueEventArgs.Index, receivedValueEventArgs.Value);
            OnNewValueEvent?.Invoke(this, new ValueChangedEventArgs(receivedValueEventArgs.Index));
        }

        private void _port_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            if (e.EventType == SerialData.Chars)
            {
                byte[] data = new byte[_port.BytesToRead];
                _port.Read(data, 0 , data.Length);
                _deserializer.ReadBytes(data);
            }
        }

        public void Open()
        {
            _port.Open();
        }

        public void Close()
        {
            _port.Close();
        }

        public class ValueChangedEventArgs : EventArgs
        {
            public int Index;
            public ValueChangedEventArgs(int index)
            {
                Index = index;
            }
        }
    }
}
