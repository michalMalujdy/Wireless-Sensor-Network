using Microsoft.AspNetCore.SignalR;
using Wsn.Infrastructure.Resources;

namespace Wsn.Web.Hubs
{
    public class ReadingsHub: Hub
    {
        public void SendLightReading(PostReadingResource resource)
        {
            Clients.All.SendCoreAsync("sendLightReading", new object[] { resource });
        }
    }
}
