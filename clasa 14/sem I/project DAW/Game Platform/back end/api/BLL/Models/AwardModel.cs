﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace api.BLL.Models
{
    public class AwardModel
    {
        public string Id { get; set; }
        public string Name { get; set; }
        public int Year { get; set; }

        public string GameId { get; set; }
    }
}
