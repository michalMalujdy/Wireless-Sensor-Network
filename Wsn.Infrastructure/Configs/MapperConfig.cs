using AutoMapper;
using Wsn.Core.Domain;
using Wsn.Infrastructure.Resources;

namespace Wsn.Infrastructure.Configs
{
    public static class MapperConfig
    {
        public static void Setup()
        {
            Mapper.Initialize(config =>
            {
                config.CreateMap<PostReadingResource, SensorReading>();
            });
        }
    }
}
