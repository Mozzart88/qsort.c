#include <qsort.h>

static void	_bzero(void *pointer, size_t size)
{
	char	*tmp;

	if (!pointer)
		return;
	tmp = (char*)pointer;
	while (size--)
		*(tmp + size) = 0;
}

__attribute__((unused)) static void	_swap(int *p1, int *p2)
{
	int	i;

	i = *p1;
	*p1 = *p2;
	*p2 = i;
}

static void _memcpy(int *src, int *dst, size_t size)
{
	if (!src || !dst)
		return;
	while (size--)
		*(dst + size) = *(src + size);
}

static unsigned int	_getPivotPoint(int size)
{
	return size % 2 + size / 2 - 1;
}

static void	_compare(int **greater, int **lesser, int pel, int val, qsort_callback cb)
{

	if (cb(val, pel))
	{
		**greater = val;
		--(*greater);
	}
	else
	{
		**lesser = val;
		++(*lesser);
	}
}
static void	_sort(int *src, int *dst, size_t size, qsort_callback cb)
{
	size_t	pivotPoint;
	size_t	i;
	int	*dels;
	int	*delb;
	int	pel;

	if (size <= 1)
		return;
	if (size <= 2)
	{
		if (size > 1 &&  cb(*dst, *(dst + 1)))
			_swap(dst, (dst + 1));
		return;
	}
	pivotPoint = _getPivotPoint(size);
	i = 0;
	pel = *(dst + pivotPoint);
	dels = dst;
	delb = dst + size - 1;
	while (i < size)
	{
		if (i != pivotPoint)
			_compare(&delb, &dels, pel, *(src + i), cb);
		++i;
	}
	pivotPoint = dels - dst;
	*dels = pel;
	_memcpy(dst, src, size);
	_sort(src, dst, pivotPoint, cb);
	_sort(src + pivotPoint, delb, size - pivotPoint, cb);
}

int 		*my_qsort(int *arr, size_t size, qsort_callback cb)
{
	int	*res;
	int	tmp[size];

	if ((res = (int*)malloc((sizeof (int)) * size)) == NULL)
		return NULL;
	_bzero(res, size);
	_memcpy(arr, &tmp[0], size);
	_memcpy(arr, res, size);
	_sort(&tmp[0], res, size, cb);
	
	return res;
}
