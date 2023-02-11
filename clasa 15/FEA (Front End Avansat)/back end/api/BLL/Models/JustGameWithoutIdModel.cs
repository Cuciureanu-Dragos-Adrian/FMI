using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace api.BLL.Models
{
    public class JustGameWithoutIdModel
    {
        public string Name { get; set; }
        public string ReleaseDate { get; set; }
        public float? Review { get; set; }
        public float? Price { get; set; }
    }
}
