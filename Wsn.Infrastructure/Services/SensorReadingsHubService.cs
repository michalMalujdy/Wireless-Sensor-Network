using System.Collections.Generic;
using System.Threading.Tasks;
using Microsoft.AspNetCore.SignalR;
using Wsn.Application.Interfaces;
using Wsn.Core.Domain;
using Wsn.Infrastructure.Hubs;

namespace Wsn.Infrastructure.Services
{
    public class SensorReadingsHubService : ISensorReadingsHubService
    {
        private readonly IHubContext<SensorReadingsHub> _readingsHub;

        public SensorReadingsHubService(IHubContext<SensorReadingsHub> readingsHub)
        {
            _readingsHub = readingsHub;
        }

        public async Task SendSensorReadingsLog(ICollection<SensorReading> readings)
        {
            await _readingsHub.Clients.All.SendCoreAsync("sendSensorReadings", new object[] { readings });
        }
    }
}
