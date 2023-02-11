using api.BLL.Interfaces;
using api.BLL.Models;
using api.DAL.Interfaces;
using api.Entities;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace api.BLL.Managers
{
    public class EventManager : IEventManager
    {
        private readonly IEventRepository repository;

        public EventManager(IEventRepository eventRepository)
        {
            this.repository = eventRepository;
        }

        public Event GetEventById(string id)
        {
            return repository.GetEventById(id);
        }

        public List<Event> GetEvents()
        {
            return repository.GetEvents();
        }

        public void Create(EventWithoutIdModel model)
        {
            repository.Create(model);
        }

        public void Update(EventModel model)
        {
            repository.Update(model);
        }

        public void Delete(string id)
        {
            repository.Delete(id);
        }
    }
}
