using System;
using System.Collections.Generic;
using System.Threading;
using System.Threading.Tasks;
using AutoMapper;
using MediatR;
using Microsoft.AspNetCore.SignalR;
using SharpRaven;
using Wsn.Core.Domain;
using Wsn.Data;
using Wsn.Web.Hubs;

namespace Wsn.Application.Features.SensorReadings.Commands.CreateReadings
{
    public class CreateSensorReadingsHandler : IRequestHandler<CreateSensorReadingsCommand>
    {
        private readonly AppDbContext _db;
        private readonly IMapper _mapper;
        private readonly IHubContext<ReadingsHub> _readingsHub;
        private readonly RavenClient _ravenClient;

        public CreateSensorReadingsHandler(
            AppDbContext db, 
            IMapper mapper, 
            IHubContext<ReadingsHub> readingsHub, 
            RavenClient ravenClient)
        {
            _db = db;
            _readingsHub = readingsHub;
            _ravenClient = ravenClient;
            _mapper = mapper;
        }

        public async Task<Unit> Handle(CreateSensorReadingsCommand command, CancellationToken cancellationToken)
        {
            //await _ravenClient.CaptureAsync(new SentryEvent("Reading received"));

            var readings = _mapper.Map<ICollection<SensorReading>>(command.Readings);
            SetCurrentDate(readings);

            _db.SensorReadings.AddRange(readings);
            await _db.SaveChangesAsync(cancellationToken);

            await SendReadingLog(readings);

            return Unit.Value;
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
