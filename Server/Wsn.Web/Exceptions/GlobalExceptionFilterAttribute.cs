using Microsoft.AspNetCore.Hosting;
using Microsoft.AspNetCore.Mvc.Filters;
using SharpRaven;
using SharpRaven.Data;

namespace MyFinanceCube.Attributes
{
    public class GlobalExceptionFilterAttribute : ExceptionFilterAttribute
    {
        private readonly RavenClient _ravenClient;
        private readonly IHostingEnvironment _environment;

        public GlobalExceptionFilterAttribute(IHostingEnvironment environment, RavenClient ravenClient)
        {
            _ravenClient = ravenClient;
            _environment = environment;
        }

        public override void OnException(ExceptionContext context)
        {
            _ravenClient.Capture(new SentryEvent(context.Exception));
        }
    }
}
