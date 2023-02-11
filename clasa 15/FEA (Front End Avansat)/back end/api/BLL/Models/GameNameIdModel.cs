using api.Entities;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace api.BLL.Models
{
    public class GameNameIdModel
    {
        public string Id { get; set; }
        public string Name { get; set; }

        public GameNameIdModel(Game game)
        {
            this.Id = game.Id;
            this.Name = game.Name;
        }
    }
}
