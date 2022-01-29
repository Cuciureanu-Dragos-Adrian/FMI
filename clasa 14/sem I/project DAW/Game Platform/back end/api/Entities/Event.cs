using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace api.Entities
{
    public class Event
    {
        public string Id { get; set; }
        public string Name { get; set; }
        public int Year { get; set; }

        public virtual ICollection<CompanyEvent> CompanyEvents { get; set; }
    }
}
