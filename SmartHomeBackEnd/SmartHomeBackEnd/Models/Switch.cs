using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace SmartHomeBackEnd.Models
{
    public class Switch
    {
        public Guid Node { get; set; }
        public Guid Id { get; set; }
        public int Number { get; set; }
    }
}
