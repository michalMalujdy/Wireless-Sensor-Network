using Microsoft.AspNetCore.Mvc;
using System;
using System.Threading.Tasks;
using Wsn.Application.Features.SensorReadings.Commands.CreateSensorReadings;
using Wsn.Application.Features.SensorReadings.Queries.GetSensorReadings;

namespace Wsn.Web.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    public class SensorReadingsController : CommandQueryControllerBase
    {
        /// <summary>
        /// Receives a reading from light sensor.
        /// </summary>
        [HttpPost]
        [ProducesResponseType(200)]
        [ProducesResponseType(400)]
        [ProducesResponseType(404)]
        public async Task<IActionResult> CreateSensorReadings(
            [FromBody] CreateSensorReadingsCommand command)
        {
            await Mediator.Send(command);
            return Ok();
        }

        /// <summary>
        /// Returns a collection of readings from sensors.
        /// </summary>
        [HttpGet]
        [ProducesResponseType(200)]
        [ProducesResponseType(400)]
        [ProducesResponseType(404)]
        public async Task<IActionResult> GetReadings(
            [FromBody] GetSensorReadingsQuery query)
        {
            var readings = await Mediator.Send(query);
            return Ok(readings);
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