// Scroll fade-in
const fadeEls = document.querySelectorAll('.fade-in');
const fadeObserver = new IntersectionObserver((entries) => {
  entries.forEach((e, i) => {
    if (e.isIntersecting) {
      setTimeout(() => e.target.classList.add('visible'), i * 60);
      fadeObserver.unobserve(e.target);
    }
  });
}, { threshold: 0.12 });
fadeEls.forEach(el => fadeObserver.observe(el));

// Respect prefers-reduced-motion: replace autoplay demo loops with their poster frame
if (window.matchMedia('(prefers-reduced-motion: reduce)').matches) {
  document.querySelectorAll('video[autoplay]').forEach((video) => {
    video.removeAttribute('autoplay');
    video.pause();
  });
}

// Projects page: category filtering
const projRoot = document.querySelector('.proj-page');
if (projRoot) {
  const cards = Array.from(projRoot.querySelectorAll('[data-card]'));
  const headers = Array.from(projRoot.querySelectorAll('[data-head]'));
  const boxes = Array.from(projRoot.querySelectorAll('[data-groupbox]'));
  const courselists = Array.from(projRoot.querySelectorAll('[data-courselist]'));
  const chips = Array.from(projRoot.querySelectorAll('[data-filter]'));
  const emptyEl = projRoot.querySelector('[data-empty]');
  const isVisible = (el) => el && !el.hidden;

  const applyFilter = (filter) => {
    chips.forEach((chip) => {
      const active = chip.getAttribute('data-filter') === filter;
      chip.classList.toggle('active', active);
      chip.setAttribute('aria-pressed', String(active));
    });
    cards.forEach((card) => {
      const cats = (card.getAttribute('data-cat') || '').split(' ');
      card.hidden = !(filter === 'all' || cats.includes(filter));
    });
    courselists.forEach((list) => { list.hidden = filter !== 'all'; });
    boxes.forEach((box) => {
      const group = box.getAttribute('data-groupbox');
      box.hidden = !cards.some((c) => c.getAttribute('data-group') === group && isVisible(c));
    });
    headers.forEach((header) => {
      const group = header.getAttribute('data-head');
      const hasCard = cards.some((c) => c.getAttribute('data-group') === group && isVisible(c));
      const hasList = courselists.some((l) => l.getAttribute('data-group') === group && isVisible(l));
      header.hidden = !(hasCard || hasList);
    });
    if (emptyEl) emptyEl.hidden = cards.some(isVisible) || courselists.some(isVisible);
  };

  chips.forEach((chip) => chip.addEventListener('click', () => applyFilter(chip.getAttribute('data-filter'))));
}

// Coursework page: accordion outcomes
document.querySelectorAll('[data-acc]').forEach((toggle) => {
  const course = toggle.closest('[data-course]');
  const panel = course && course.querySelector('[data-acc-panel]');
  if (!panel) return;
  toggle.addEventListener('click', () => {
    const open = course.getAttribute('data-open') === '1';
    course.setAttribute('data-open', open ? '0' : '1');
    panel.classList.toggle('open', !open);
    toggle.setAttribute('aria-expanded', String(!open));
  });
});
