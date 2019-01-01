using System.Collections.Generic;
using MediatR;
using Wsn.Core.Domain;

namespace Wsn.Application.Features.SensorReadings.Commands.CreateReadings
{
    public class CreateSensorReadingsCommand : IRequest
    {
        public ICollection<Reading> Readings { get; set; }

        public class Reading
        {
            public int DeviceId { get; set; }
            public int Value { get; set; }
            public DataType DataType { get; set; }
        }
    }
}
