using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using System.Collections.Concurrent;
using SmartHomeBackEnd.Core;
using SmartHomeBackEnd.Models;

namespace SmartHomeBackEnd.Controllers
{
    [Route("api/[controller]")]
    public class StatusController : Controller
    {
        private static ConcurrentDictionary<Guid, StatusRequest> CurrentStatus = new ConcurrentDictionary<Guid, StatusRequest>();
        private static ConcurrentDictionary<Guid, ConcurrentQueue<StatusResponse>> Messages = new ConcurrentDictionary<Guid, ConcurrentQueue<StatusResponse>>();

        [HttpGet]
        public List<StatusResponse> Get([FromQuery]StatusRequest request)
        {
            CurrentStatus[request.Node] = request;
            var list = new List<StatusResponse>();
            if (Messages.TryGetValue(request.Node, out ConcurrentQueue<StatusResponse> queue))
            {
                while (queue.TryDequeue(out StatusResponse status))
                {
                    list.Add(status);
                }
            }

            return list;
        }

        [HttpPost]
        public void Post([FromQuery]MessageRequest value)
        {
            var s = SwitchNodeMapping.Get(value.SwitchId);

            var queue = new ConcurrentQueue<StatusResponse>();
            queue = Messages.GetOrAdd(s.Node, queue);
            queue.Enqueue(new StatusResponse
            {
                Status = value.IsOn ? 1 : 0,
                SwitchName = $"switch_{s.Number}"
            });
        }
    }

    public class StatusResponse
    {
        public string SwitchName { get; set; }
        public int Status { get; set; }
    }

    public class MessageRequest
    {
        public Guid SwitchId { get; set; }
        public bool IsOn { get; set; }
    }

    public class StatusRequest
    {
        public Guid Node { get; set; }
        public string Pin1 { get; set; }
        public string Pin2 { get; set; }
        public string Pin3 { get; set; }
        public string Pin4 { get; set; }
    }
}
