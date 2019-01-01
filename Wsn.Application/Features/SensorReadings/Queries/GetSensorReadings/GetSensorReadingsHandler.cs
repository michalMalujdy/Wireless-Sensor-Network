using System;
using System.Linq;
using System.Threading;
using System.Threading.Tasks;
using AutoMapper.QueryableExtensions;
using MediatR;
using Microsoft.EntityFrameworkCore;
using Wsn.Application.Infrastructure;
using Wsn.Data;

namespace Wsn.Application.Features.SensorReadings.Queries.GetSensorReadings
{
    public class GetSensorReadingsHandler : IRequestHandler<GetSensorReadingsQuery, ListResult<GetSensorReadingsResult>>
    {
        private readonly AppDbContext _db;

        public GetSensorReadingsHandler(AppDbContext db)
        {
            _db = db;
        }

        public async Task<ListResult<GetSensorReadingsResult>> Handle(
            GetSensorReadingsQuery query, CancellationToken token)
        {
            if (query.From > query.To)
            {
                throw new ArgumentException("The 'from' date cannot be greater than 'to' date");
            }

            var readings = await _db.SensorReadings
                .Where(sr =>
                    sr.Date >= query.From &&
                    sr.Date <= query.To &&
                    sr.DataType == query.DataType)
                .ProjectTo<GetSensorReadingsResult>()
                .ToListAsync(token);

            return new ListResult<GetSensorReadingsResult>()
            {
                Items = readings,
                TotalCount = readings.Count
            };
        }
    }
}
