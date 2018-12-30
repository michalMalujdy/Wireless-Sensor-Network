using System;
using AutoMapper;
using Microsoft.AspNetCore.SignalR;
using Microsoft.EntityFrameworkCore;
using SharpRaven;
using SharpRaven.Data;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using AutoMapper.QueryableExtensions;
using Wsn.Core.Domain;
using Wsn.Data;
using Wsn.Infrastructure.Resources;
using Wsn.Infrastructure.Services.Interfaces;
using Wsn.Web.Hubs;

namespace Wsn.Infrastructure.Services.Implementations
{
    public class ReadingService : IReadingsService
    {
        private readonly AppDbContext _db;
        private readonly IHubContext<ReadingsHub> _readingsHub;
        private readonly RavenClient _ravenClient;

        public ReadingService(AppDbContext db, IHubContext<ReadingsHub> readingsHub, RavenClient ravenClient)
        {
            _db = db;
            _readingsHub = readingsHub;
            _ravenClient = ravenClient;
        }

        public async Task PostReadings(PostReadingsResource resource)
        {
            await _ravenClient.CaptureAsync(new SentryEvent("Reading received"));

            var readings = Mapper.Map<ICollection<SensorReading>>(resource.Readings);
            SetCurrentDate(readings);

            _db.SensorReadings.AddRange(readings);
            await _db.SaveChangesAsync();

            await SendReadingLog(readings);
        }

        public async Task<ICollection<GetReadingResource>> GetReadings(DateTimeOffset from, DateTimeOffset to, DataType type)
        {
            if (from > to)
            {
                throw new ArgumentException("The 'from' date cannot be greater than 'to' date");
            }

            var readings = await _db.SensorReadings
                .Where(sr =>
                    sr.Date >= from &&
                    sr.Date <= to &&
                    sr.DataType == type)
                .ToListAsync();

            var resource = Mapper.Map<ICollection<GetReadingResource>>(readings);

            return resource;
        }

        private void SetCurrentDate(ICollection<SensorReading> readings)
        {
            foreach (var reading in readings)
            {
                reading.Date = DateTimeOffset.Now;
            }
        }

        private async Task SendReadingLog(ICollection<SensorReading> readings)
        {
            await _readingsHub.Clients.All.SendCoreAsync("sendLightReading", new object[] { readings });
        }
    }
}
