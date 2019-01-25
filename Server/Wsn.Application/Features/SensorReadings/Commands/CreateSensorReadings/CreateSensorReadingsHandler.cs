using System;
using System.Collections.Generic;
using System.Threading;
using System.Threading.Tasks;
using AutoMapper;
using MediatR;
using Wsn.Application.Interfaces;
using Wsn.Core.Domain;
using Wsn.Data;

namespace Wsn.Application.Features.SensorReadings.Commands.CreateSensorReadings
{
    public class CreateSensorReadingsHandler : IRequestHandler<CreateSensorReadingsCommand>
    {
        private readonly AppDbContext _db;
        private readonly IMapper _mapper;
        private readonly ISensorReadingsHubService _hubService;

        public CreateSensorReadingsHandler(
            AppDbContext db, 
            IMapper mapper,
            ISensorReadingsHubService hubService)
        {
            _db = db;
            _mapper = mapper;
            _hubService = hubService;
        }

        public async Task<Unit> Handle(CreateSensorReadingsCommand command, CancellationToken cancellationToken)
        {
            //await _ravenClient.CaptureAsync(new SentryEvent("Reading received"));

            var readings = _mapper.Map<ICollection<SensorReading>>(command.Readings);
            SetCurrentDate(readings);

            _db.SensorReadings.AddRange(readings);
            await _db.SaveChangesAsync(cancellationToken);

            await _hubService.SendSensorReadingsLog(readings);

            return Unit.Value;
        }

        private void SetCurrentDate(ICollection<SensorReading> readings)
        {
            foreach (var reading in readings)
            {
                reading.Date = DateTimeOffset.Now;
            }
        }
    }
}
