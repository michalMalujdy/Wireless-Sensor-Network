using System;
using System.ComponentModel.DataAnnotations.Schema;

namespace Wsn.Core.Domain
{
    public class SensorReading
    {
        [DatabaseGenerated(DatabaseGeneratedOption.Identity)]
        public int Id { get; set; }

        public int DeviceId { get; set; }

        public int Value { get; set; }

        public DataType DataType { get; set; }

        public DateTimeOffset Date { get; set; }
    }
}
