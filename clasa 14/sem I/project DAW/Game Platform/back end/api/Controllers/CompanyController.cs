using api.BLL.Interfaces;
using api.BLL.Models;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Authorization;

namespace api.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    public class CompanyController : ControllerBase
    {
        private readonly ICompanyManager manager;

        public CompanyController(ICompanyManager companyManager)
        {
            this.manager = companyManager;
        }

        [HttpGet("companies")]
        [Authorize(Policy = "BasicUser")]
        public async Task<IActionResult> GetCompanies()
        {
            var companies = manager.GetCompanies();

            return Ok(companies);
        }

        [HttpGet("filterById/{id}")]
        [Authorize(Policy = "BasicUser")]
        public async Task<IActionResult> GetCompanyById([FromRoute] string id)
        {
            var company = manager.GetCompanyById(id);

            return Ok(company);
        }

        [HttpGet("filterByEventId/{eventId}")]
        [Authorize(Policy = "BasicUser")]
        public async Task<IActionResult> GetCompanyByEventId([FromRoute] string eventId)
        {
            var companies = manager.GetCompanyByEventId(eventId);

            return Ok(companies);
        }

        [HttpPost("company")]
        [Authorize(Policy = "Admin")]
        public async Task<IActionResult> Create([FromBody] CompanyWithoutIdModel model)
        {
            manager.Create(model);

            return Ok();
        }

        [HttpPost("companyAndHeadquarter")]
        [Authorize(Policy = "Admin")]
        public async Task<IActionResult> CreateCompanyAndHeadquarter([FromBody] CompanyAndHeadquarterModel model)
        {
            manager.CreateCompanyAndHeadquarter(model);

            var companies = manager.GetCompanies();
            return Ok(companies);
        }

        [HttpPut("company")]
        [Authorize(Policy = "Admin")]
        public async Task<IActionResult> Update([FromBody] CompanyModel model)
        {
            manager.Update(model);

            return Ok();
        }

        [HttpPut("companyAndHeadquarter")]
        [Authorize(Policy = "Admin")]
        public async Task<IActionResult> UpdateCompanyAndHeadquarter([FromBody] CompanyHeadquarterModel model)
        {
            manager.UpdateCompanyAndHeadquarter(model);

            var companies = manager.GetCompanies();
            return Ok(companies);
        }

        [HttpDelete("{id}")]
        [Authorize(Policy = "Admin")]
        public async Task<IActionResult> Delete([FromRoute] string id)
        {
            manager.Delete(id);

            return Ok();
        }

        [HttpDelete("companyAndHeadquarter{id}")]
        [Authorize(Policy = "Admin")]
        public async Task<IActionResult> DeleteCompanyAndHeadquarter([FromRoute] string id)
        {
            manager.DeleteCompanyAndHeadquarter(id);

            var companies = manager.GetCompanies();
            return Ok(companies);
        }
    }
}
