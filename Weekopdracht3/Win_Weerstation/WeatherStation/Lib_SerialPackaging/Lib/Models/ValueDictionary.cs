using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lib_SerialPackaging.Lib.Models
{
    public abstract class ValueDictionary
    {

        private TypeStaticValue[] _values = new TypeStaticValue[256];

        public EventHandler<ValueColelctionChangedEventArgs> _lister;

        public ValueDictionary()
        {

        }

        protected void setValue(int index, byte value)
        {
            _values[index] = new TypeStaticValue(value);
            triggerListner(index);
        }

        protected void setValue(int index, int value)
        {
            _values[index] = new TypeStaticValue(value);
            triggerListner(index);
        }

        protected void setValue(int index, char value)
        {
            _values[index] = new TypeStaticValue(value);
            triggerListner(index);
        }

        protected void setValue(int index, String value)
        {
            _values[index] = new TypeStaticValue(value);
            triggerListner(index);
        }

        protected void setValue(int index, TypeStaticValue value)
        {
            _values[index] = value;
            triggerListner(index);
        }

        public TypeStaticValue getValue(int index)
        {
            return _values[index];
        }

        private void triggerListner(int index)
        {
            if (_lister != null)
            {
                _lister?.Invoke(this, new ValueColelctionChangedEventArgs(index));
            }
        }

        public class ValueColelctionChangedEventArgs : EventArgs
        {
            public int index;

            public ValueColelctionChangedEventArgs(int i)
            {
                index = i;
            }
        }
}
}
