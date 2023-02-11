using api.BLL.Models;
using api.Entities;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace api.BLL.Interfaces
{
    public interface IEventManager
    {
        Event GetEventById(string id);
        List<Event> GetEvents();
        void Create(EventWithoutIdModel model);
        void Update(EventModel model);
        void Delete(string id);
    }
}
