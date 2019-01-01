using System;
using MediatR;
using Wsn.Application.Infrastructure;
using Wsn.Core.Domain;

namespace Wsn.Application.Features.SensorReadings.Queries.GetSensorReadings
{
    public class GetSensorReadingsQuery : IRequest<ListResult<GetSensorReadingsResult>>
    {
        public DateTimeOffset From { get; set; }
        public DateTimeOffset To { get; set; }
        public DataType DataType { get; set; }
    }
}
