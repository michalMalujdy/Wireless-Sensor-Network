using Wsn.Core.Domain;

namespace Wsn.Infrastructure.Resources
{
    public class PostReadingResource
    {
        public int DeviceId { get; set; }
        public int Value { get; set; }
        public DataType DataType { get; set; }
    }
}
