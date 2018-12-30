using System;
using System.Collections.Generic;
using System.Threading.Tasks;
using Wsn.Core.Domain;
using Wsn.Infrastructure.Resources;

namespace Wsn.Infrastructure.Services.Interfaces
{
    public interface IReadingsService
    {
        Task PostReadings(PostReadingsResource resource);
        Task<ICollection<GetReadingResource>> GetReadings(DateTimeOffset from, DateTimeOffset to, DataType type);
    }
}
