using Microsoft.EntityFrameworkCore;
using Wsn.Core.Domain;

namespace Wsn.Data
{
    public class AppDbContext: DbContext
    {
        public DbSet<SensorReading> SensorReadings { get; set; }

        public AppDbContext(DbContextOptions<AppDbContext> options) : base(options)
        {
        }
    }
}
