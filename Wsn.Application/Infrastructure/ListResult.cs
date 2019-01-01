using System.Collections.Generic;

namespace Wsn.Application.Infrastructure
{
    public class ListResult<T>
    {
        public ICollection<T> Items { get; set; }
        public int TotalCount { get; set; }
    }
}
