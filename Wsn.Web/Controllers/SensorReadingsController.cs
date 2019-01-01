using Microsoft.AspNetCore.Mvc;
using System;
using System.Threading.Tasks;
using Wsn.Application.Features.SensorReadings.Commands.CreateReadings;
using Wsn.Core.Domain;
using Wsn.Infrastructure.Resources;
using Wsn.Infrastructure.Services.Interfaces;

namespace Wsn.Web.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    public class SensorReadingsController : CommandQueryControllerBase
    {
        private readonly IReadingsService _readingsService;

        public SensorReadingsController(IReadingsService readingsService)
        {
            _readingsService = readingsService;
        }

        /// <summary>
        /// Receives a reading from light sensor.
        /// </summary>
        [HttpPost]
        [ProducesResponseType(200)]
        [ProducesResponseType(400)]
        [ProducesResponseType(404)]
        public async Task<IActionResult> CreateSensorReadings(CreateSensorReadingsCommand command)
        {
            //await _readingsService.PostReadings(resource);

            await Mediator.Send(command);

            return Ok();
        }

        /// <summary>
        /// Returns a collection of readings from light sensors.
        /// </summary>
        [HttpGet]
        [ProducesResponseType(200)]
        [ProducesResponseType(400)]
        [ProducesResponseType(404)]
        public async Task<IActionResult> GetReadings(
            [FromQuery] DateTimeOffset from,
            [FromQuery] DateTimeOffset to,
            [FromQuery] DataType dataType)
        {
            return Ok(await _readingsService.GetReadings(from, to, dataType));
        }

        /// <summary>
        /// Test exception
        /// </summary>
        [HttpGet]
        [Route("Exception")]
        [ProducesResponseType(500)]
        public IActionResult Exception ()
        {
            throw new Exception("Test exception");
        }
    }
}