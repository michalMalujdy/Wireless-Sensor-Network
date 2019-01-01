using AutoMapper;
using Wsn.Application.Features.SensorReadings.Commands.CreateReadings;
using Wsn.Core.Domain;

namespace Wsn.Application.Features.SensorReadings
{
    public class SensorReadingMappings : Profile
    {
        public SensorReadingMappings()
        {
            CreateMap<CreateSensorReadingsCommand.Reading, SensorReading>();
        }
    }
}
