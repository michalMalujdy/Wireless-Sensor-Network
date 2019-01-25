using System;
using Wsn.Core.Domain;

namespace Wsn.Application.Features.SensorReadings.Queries.GetSensorReadings
{
    public class GetSensorReadingsResult
    {
        public int Id { get; set; }

        public int DeviceId { get; set; }

        public int Value { get; set; }

        public DataType DataType { get; set; }

        public DateTimeOffset Date { get; set; }
    }
}
