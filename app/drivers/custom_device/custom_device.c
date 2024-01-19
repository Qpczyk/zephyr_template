/** @file
 * Copyright (C) 2022 <author>
 *
 * These computer program listings and specifications, are the property of
 * <author> and shall not be reproduced or copied or used in
 * whole or in part without written permission from <author>
 *
 * @author Mateusz Kupczyk
 */

#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(custom_device, LOG_LEVEL_INF);

#include <zephyr/drivers/gpio.h>
#include <zephyr/pm/device.h>

#define DT_DRV_COMPAT custom_device

struct device_config {
	const struct gpio_dt_spec device_gpio;
};

static int custom_device_init(const struct device *dev)
{
	const struct device_config *const config = dev->config;

	return gpio_pin_configure_dt(&(config->device_gpio), GPIO_OUTPUT);
}

/* use power management api to change device state */
static int custom_device_pm_control(const struct device *dev, enum pm_device_action action)
{
	const struct device_config *const config = dev->config;

	switch (action) {
	case PM_DEVICE_ACTION_TURN_ON:
	case PM_DEVICE_ACTION_RESUME:
		return gpio_pin_set_dt(&(config->device_gpio), true);
	case PM_DEVICE_ACTION_TURN_OFF:
	case PM_DEVICE_ACTION_SUSPEND:
		return gpio_pin_set_dt(&(config->device_gpio), false);
	default:
		return -ENOTSUP;
	}

	return 0;
}

#if DT_NUM_INST_STATUS_OKAY(DT_DRV_COMPAT) == 0
#warning "Custom device driver is enabled but no devices in DTS"
#endif

#define CUSTOM_DEVICE_INSTANCE(inst)                                                               \
	static const struct device_config custom_device_##inst##_config = {                        \
		.device_gpio = GPIO_DT_SPEC_INST_GET(inst, device_gpios),                          \
	};                                                                                         \
                                                                                                   \
	PM_DEVICE_DT_INST_DEFINE(inst, custom_device_pm_control);                                  \
                                                                                                   \
	DEVICE_DT_INST_DEFINE(inst, custom_device_init, PM_DEVICE_DT_INST_GET(inst), NULL,         \
			      &custom_device_##inst##_config, POST_KERNEL,                         \
			      CONFIG_CUSTOM_DEVICE_INIT_PRIORITY, NULL)

DT_INST_FOREACH_STATUS_OKAY(CUSTOM_DEVICE_INSTANCE);
