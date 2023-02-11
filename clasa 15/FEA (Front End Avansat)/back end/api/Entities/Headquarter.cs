using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace api.Entities
{
    public class Headquarter
    {
        public string Id { get; set; }
        public string Country { get; set; }
        public string City { get; set; }
        public string Street { get; set; }

        public virtual Company Company { get; set; }
    }
}
