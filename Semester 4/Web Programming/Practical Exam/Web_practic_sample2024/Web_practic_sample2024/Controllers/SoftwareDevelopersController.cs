using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.Rendering;
using Microsoft.EntityFrameworkCore;
using Web_practic_sample2024.Data;
using Web_practic_sample2024.Models;

namespace Web_practic_sample2024.Controllers
{
    public class SoftwareDevelopersController : Controller
    {
        private readonly ApplicationDbContext _context;

        public SoftwareDevelopersController(ApplicationDbContext context)
        {
            _context = context;
        }

        // GET: SoftwareDevelopers
        public async Task<IActionResult> Index()
        {
            return View(await _context.SoftwareDevelopers.ToListAsync());
        }

        // GET: SoftwareDevelopers/Details/5
        public async Task<IActionResult> Details(int? id)
        {
            if (id == null)
            {
                return NotFound();
            }

            var softwareDeveloper = await _context.SoftwareDevelopers
                .FirstOrDefaultAsync(m => m.Id == id);
            if (softwareDeveloper == null)
            {
                return NotFound();
            }

            return View(softwareDeveloper);
        }

        // GET: SoftwareDevelopers/Create
        public IActionResult Create()
        {
            return View();
        }

        // POST: SoftwareDevelopers/Create
        // To protect from overposting attacks, enable the specific properties you want to bind to.
        // For more details, see http://go.microsoft.com/fwlink/?LinkId=317598.
        [HttpPost]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> Create([Bind("Id,Name,Age,Skills")] SoftwareDeveloper softwareDeveloper)
        {
            if (ModelState.IsValid)
            {
                _context.Add(softwareDeveloper);
                await _context.SaveChangesAsync();
                return RedirectToAction(nameof(Index));
            }
            return View(softwareDeveloper);
        }

        // GET: SoftwareDevelopers/Edit/5
        public async Task<IActionResult> Edit(int? id)
        {
            if (id == null)
            {
                return NotFound();
            }

            var softwareDeveloper = await _context.SoftwareDevelopers.FindAsync(id);
            if (softwareDeveloper == null)
            {
                return NotFound();
            }
            return View(softwareDeveloper);
        }

        // POST: SoftwareDevelopers/Edit/5
        // To protect from overposting attacks, enable the specific properties you want to bind to.
        // For more details, see http://go.microsoft.com/fwlink/?LinkId=317598.
        [HttpPost]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> Edit(int id, [Bind("Id,Name,Age,Skills")] SoftwareDeveloper softwareDeveloper)
        {
            if (id != softwareDeveloper.Id)
            {
                return NotFound();
            }

            if (ModelState.IsValid)
            {
                try
                {
                    _context.Update(softwareDeveloper);
                    await _context.SaveChangesAsync();
                }
                catch (DbUpdateConcurrencyException)
                {
                    if (!SoftwareDeveloperExists(softwareDeveloper.Id))
                    {
                        return NotFound();
                    }
                    else
                    {
                        throw;
                    }
                }
                return RedirectToAction(nameof(Index));
            }
            return View(softwareDeveloper);
        }

        // GET: SoftwareDevelopers/Delete/5
        public async Task<IActionResult> Delete(int? id)
        {
            if (id == null)
            {
                return NotFound();
            }

            var softwareDeveloper = await _context.SoftwareDevelopers
                .FirstOrDefaultAsync(m => m.Id == id);
            if (softwareDeveloper == null)
            {
                return NotFound();
            }

            return View(softwareDeveloper);
        }

        // POST: SoftwareDevelopers/Delete/5
        [HttpPost, ActionName("Delete")]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> DeleteConfirmed(int id)
        {
            var softwareDeveloper = await _context.SoftwareDevelopers.FindAsync(id);
            if (softwareDeveloper != null)
            {
                _context.SoftwareDevelopers.Remove(softwareDeveloper);
            }

            await _context.SaveChangesAsync();
            return RedirectToAction(nameof(Index));
        }
        // GET: SoftwareDevelopers/FilterBySkill
        public async Task<IActionResult> FilterBySkill(string skill)
        {
            if (string.IsNullOrWhiteSpace(skill))
            {
                return View("Index", await _context.SoftwareDevelopers.ToListAsync());
            }

            var filteredDevelopers = await _context.SoftwareDevelopers
                .Where(d => d.Skills.Contains(skill, StringComparison.OrdinalIgnoreCase))
                .ToListAsync();

            return View("Index", filteredDevelopers);
        }

        private bool SoftwareDeveloperExists(int id)
        {
            return _context.SoftwareDevelopers.Any(e => e.Id == id);
        }
    }
}
