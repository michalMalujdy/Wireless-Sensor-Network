using MediatR;
using Microsoft.AspNetCore.Mvc;

namespace Wsn.Web.Controllers
{
    public class CommandQueryControllerBase : ControllerBase
    {
        private IMediator _mediator;

        protected IMediator Mediator => _mediator ?? (_mediator = InstantiateMediator());

        private IMediator InstantiateMediator()
        {
            return (IMediator) HttpContext.RequestServices.GetService(typeof(IMediator));
        }
    }
}
