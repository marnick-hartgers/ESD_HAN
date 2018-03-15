using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lib_SerialPackaging.Lib.Models
{
    public class TypeStaticValue
    {
        private StaticType type;
        private byte byteValue;
        private char charValue;
        private int intValue;
        private String stringValue = null;

        public TypeStaticValue(byte value)
        {
            type = StaticType.BYTE;
            byteValue = value;
        }

        public TypeStaticValue(int value)
        {
            type = StaticType.INT;
            intValue = value;
        }

        public TypeStaticValue(char value)
        {
            type = StaticType.CHAR;
            charValue = value;
        }

        public TypeStaticValue(String value)
        {
            type = StaticType.STRING;
            stringValue = value;
        }

        public StaticType getType()
        {
            return type;
        }

        public byte getByteValue()
        {
            if (type != StaticType.BYTE)
            {
                throw new InvalTypeExeption(StaticType.BYTE);
            }
            return byteValue;
        }


        public int getIntValue()
        {
            if (type != StaticType.INT)
            {
                throw new InvalTypeExeption(StaticType.INT);
            }
            return intValue;
        }

        public char getCharValue()
        {
            if (type != StaticType.CHAR)
            {
                throw new InvalTypeExeption(StaticType.CHAR);
            }
            return charValue;
        }

        public String getStringValue()
        {
            if (type != StaticType.STRING)
            {
                throw new InvalTypeExeption(StaticType.STRING);
            }
            return stringValue;
        }

        public enum StaticType
        {
            BYTE, INT, CHAR, STRING
        }

        class InvalTypeExeption : Exception
        {
            public InvalTypeExeption(StaticType type)
            {

            }
        }

        public string ToString()
        {
            try
            {
                switch (type)
                {
                    case StaticType.BYTE:
                        return "Byte: " + getByteValue();
                    case StaticType.INT:
                        return "Int: " + getIntValue();
                    case StaticType.CHAR:
                        return "Char: " + getCharValue();
                    case StaticType.STRING:
                        return "String: " + getStringValue();

                }
            }
            catch (InvalTypeExeption invalTypeExeption)
            {
                throw;
            }
            return "";
        }
    }
}
