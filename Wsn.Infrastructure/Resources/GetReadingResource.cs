using System;
using Wsn.Core.Domain;

namespace Wsn.Infrastructure.Resources
{
    public class GetReadingResource
    {
        public int Id { get; set; }

        public int DeviceId { get; set; }

        public int Value { get; set; }

        public DataType DataType { get; set; }

        public DateTimeOffset Date { get; set; }
    }
}
