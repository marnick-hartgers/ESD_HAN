using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Lib_SerialPackaging.Lib.Models;

namespace Lib_SerialPackaging.Lib
{
    public class PackageDeserializer
    {

        private byte _startByte = (byte)0xAA;
        public EventHandler<ReceivedValueEventArgs> onNewValue;

        byte[] _readBuffer = new byte[2048];
        int _writeIndex = 0;
        int _readIndex = 0;


        public void ReadBytes(byte[] bytes)
        {
            for (int i = 0; i < bytes.Length; i++)
            {

                _readBuffer[_writeIndex] = bytes[i];
                _writeIndex++;
                if (_writeIndex >= _readBuffer.Length)
                {
                    throw new Exception("Buffer overflow");
                }
            }
            checkForData();
        }

        private void checkForData()
        {
            int startbyteIndex = -1;

            for (int readIndex = _readIndex; readIndex < _writeIndex; readIndex++)
            {
                if (startbyteIndex == -1 && _readBuffer[readIndex] == 0xAA)
                {
                    startbyteIndex = readIndex;
                    int length = tryReadPackage(startbyteIndex);
                    _readIndex = startbyteIndex + length;
                    startbyteIndex = -1;
                }
            }
            if (_readIndex > 0)
            {
                clearReadedBuffer();
            }
        }

        private void clearReadedBuffer()
        {
            byte[] tempBuffer = new byte[2048];
            for (int i = _readIndex; i < _readBuffer.Length;i++)
            {
                tempBuffer[i - _readIndex] = _readBuffer[i];
            }
            _readBuffer = tempBuffer;
            _writeIndex -= _readIndex;
            _readIndex = 0;
        }

        private int tryReadPackage(int start)
        {
            if (_writeIndex - start > 6)
            {
                int packLength = parseUInt(_readBuffer[start + 1], _readBuffer[start + 2]);
                if (_writeIndex - start >= packLength)
                {
                    bool success = parseValue(start + 3, _readIndex + packLength);
                    return success ? packLength : 0;
                }
            }
            return 0;
        }

        private bool parseValue(int begin, int end)
        {
            byte typebyte = _readBuffer[begin + 1];
            byte index = _readBuffer[begin];
            TypeStaticValue value = null;
            try
            {
                switch (typebyte)
                {
                    case 0x0:
                        value = new TypeStaticValue(_readBuffer[begin + 2]);
                        break;
                    case 0x1:
                        value = new TypeStaticValue(parseUInt(_readBuffer[begin + 2], _readBuffer[begin + 3]));
                        break;
                    case 0x2:
                        value = new TypeStaticValue((char)_readBuffer[begin + 2]);
                        break;
                    case 0x3:
                        value = new TypeStaticValue(parseString(begin + 2, end));
                        break;
                }
            }
            catch (Exception err)
            {

            }
            if (value != null)
            {
                emitNewValue(index, value);
                return true;
            }
            else
            {
                return false;
            }

        }

        private void emitNewValue(int index, TypeStaticValue v)
        {
            onNewValue?.Invoke(this, new ReceivedValueEventArgs(index, v));
        }

        private int parseUInt(byte highByte, byte lowByte)
        {
            return (UInt16)lowByte + ((UInt16)highByte << 8);
        }

        private String parseString(int begin, int end)
        {
            if (begin + 2 <= end || _writeIndex < end)
            {
                //throw new Exception("String incomplete");
            }
            int length = parseUInt(_readBuffer[begin], _readBuffer[begin + 1]);
            StringBuilder sb = new StringBuilder();
            for (int i = 0; i < length; i++)
            {
                sb.Append((char)_readBuffer[begin + 2 + i]);
            }
            return sb.ToString();
        }

        public class ReceivedValueEventArgs : EventArgs
        {
            public TypeStaticValue Value;
            public int Index;

            public ReceivedValueEventArgs(int index, TypeStaticValue value)
            {
                Index = index;
                Value = value;
            }

        }

    }
}
