using System.Collections.Generic;
using System.Threading.Tasks;
using Wsn.Core.Domain;

namespace Wsn.Application.Interfaces
{
    public interface ISensorReadingsHubService
    {
        Task SendSensorReadingsLog(ICollection<SensorReading> readings);
    }
}
