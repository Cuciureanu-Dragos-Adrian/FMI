using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace api.Entities
{
    public class CompanyEvent
    {
        public string CompanyId { get; set; }
        public string EventId { get; set; }

        public virtual Company Company { get; set; }
        public virtual Event Event { get; set; }
    }
}
