using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Http;
using Microsoft.Extensions.Logging;
using Web_practic_auctions.Models;

namespace Web_practic_auctions.Controllers
{
    public class HomeController : Controller
    {
        private readonly ILogger<HomeController> _logger;

        public HomeController(ILogger<HomeController> logger)
        {
            _logger = logger;
        }

        public IActionResult Index()
        {
            return View();
        }

        [HttpPost]
        public IActionResult Index(string username)
        {
            // Set the username in session or TempData
            TempData["Username"] = username;

            // Redirect to the Index action in the AuctionsController
            return RedirectToAction("Index", "Auctions");
        }
    }
}
